import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute(
        """SELECT stocks.stock, stocks.shares, stocks.price, stocks.total, users.cash, (SUM(stocks.price * stocks.shares) + users.cash) AS total_assets FROM stocks JOIN users ON stocks.user_id = users.id WHERE users.id = ? GROUP BY stocks.stock, stocks.shares, stocks.price, stocks.user_id""", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total_assets = cash + sum(row["price"] * row["shares"] for row in rows)
    return render_template("index.html", rows=rows, cash=cash, total_assets=total_assets)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = request.form.get("symbol")
        if not quote or lookup(quote) == None:
            return apology("Invalid stock quote", 400)

        share = float(request.form.get("shares"))
        if not share or share < 1:
            return apology("Enter a vaid share amount", 400)
        stock = lookup(quote)
        price = stock["price"] * share
        result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = float(result[0]["cash"])

        if cash < price:
            return apology("Not enough cash", 400)
        else:
            db.execute("INSERT INTO stocks (user_id, stock, shares, price) VALUES (?, ?, ?, ?)",
                       session["user_id"], stock["symbol"], share, stock["price"])
            result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = float(result[0]["cash"]) - price
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # log the transaction
        db.execute("INSERT INTO transactions (user_id, stock, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'buy')",
                   session["user_id"], stock["symbol"], share, stock["price"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT stock, shares, price, transaction_type, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", session["user_id"])
    return render_template("/history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()
    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("Not a vaid stock symbol", 400)
        else:
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("the passwords didn't match", 400)
        username = db.execute("SELECT username FROM users WHERE username = ?",
                              request.form.get("username"))
        if username:
            return apology("username taken, please select another", 400)

        # Store the username and password into the database
        hash_password = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   request.form.get("username"), hash_password)

        session["user_id"] = request.form.get("id")

        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Valitate the correctness of user input of stock symbol
        quote = request.form.get("symbol")
        owned_stocks = db.execute("SELECT stock FROM stocks WHERE user_id = ?", session["user_id"])
        if not any(stock['stock'] == quote for stock in owned_stocks):
            return apology("Cannot sell a stock you don't own", 400)

        # Validate the amount of shares user inputed
        share = int(request.form.get("shares"))
        owned_shares = db.execute(
            "SELECT shares FROM stocks WHERE user_id = ? AND stock = ?", session["user_id"], quote)
        if owned_shares:
            owned_share = int(owned_shares[0]["shares"])
            if not share or share < 1:
                return apology("Enter a valid share amount", 400)
            elif share > owned_share:
                return apology("Not enough shares", 400)
        else:
            return apology("Not enough shares", 400)

        # Quering the database to reflect the sale

        # Remove the whole row if user sells all shares
        if share == owned_share:
            # Get the value of sold shares
            stock = lookup(quote)

            share_value = stock["price"] * share
            # Update the total cash
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                       share_value, session["user_id"])

            # Remove the row form stocks
            db.execute("DELETE FROM stocks WHERE user_id = ? AND stock = ?",
                       session["user_id"], quote)

        # Update the row accordingly
        else:
            # Get the value of sold shares
            stock = lookup(quote)
            share_value = stock["price"] * share
            # Decrese the amount of shares user sold
            db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? AND stock = ?",
                       share, session["user_id"], quote)
            # Update the user cash
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                       share_value, session["user_id"])

        # log the transaction
        db.execute("INSERT INTO transactions (user_id, stock, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'sell')",
                   session["user_id"], quote, share, stock["price"])

        return redirect("/")
    else:
        return render_template("sell.html")
