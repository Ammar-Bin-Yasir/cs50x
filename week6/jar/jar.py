class Jar:
    # Initialization of Jar
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Invalid Capacity")
        self._capacity = capacity

        # There are no cookies initially
        self._cookies = 0

    # For print()
    def __str__(self):
        num_cookie = "🍪"*self._cookies
        return num_cookie

    # Method to add cookies
    def deposit(self, n):
        if self._cookies + n > self._capacity:
            raise ValueError("Jar Full")
        self._cookies += n

    # Method to remove cookies
    def withdraw(self, n):
        if self._cookies - n < 0:
            raise ValueError("Jar Empty")
        self._cookies -= n

    # Attribute that tells the current cookies in the Jar
    @property
    def size(self):
        return self._cookies

    # Setting the total Capacity of the jar
    @property
    def capacity(self):
        return self._capacity
