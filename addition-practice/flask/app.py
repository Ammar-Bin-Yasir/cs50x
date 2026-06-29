# Moves default value to template

from flask import Flask, render_template, request

# Tells the framework to treat my file as web application
app = Flask(__name__)


# Defines a route that implies that whenever user visits "/" the function index should be called.
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
    return render_template("index.html")
































