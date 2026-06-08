from flask import Flask
from flask import render_template
from flask import request

import sys
import os

sys.path.append(
    os.path.abspath(
        os.path.join(
            os.path.dirname(__file__),
            "..",
            "src"
        )
    )
)

from flask import Flask
from flask import render_template
from flask import request

from backend import (
    prime_test,
    generate_rsa,
    register_user,
    authenticate_user,
    get_stats,
    run_carmichael_demo,
    benchmark_number
)

app = Flask(__name__)


@app.route("/")
def home():

    return render_template(
        "index.html"
    )


@app.route(
    "/register",
    methods=["GET", "POST"]
)
def register():

    if request.method == "POST":

        username = request.form["username"]

        register_user(username)

        keypair = generate_rsa()

        print("\n====================")
        print("RSA RESULT")
        print("====================")
        print(keypair)
        print("====================\n")

        return render_template(
            "certificate.html",
            username=username,
            keypair=keypair
        )

    return render_template(
        "register.html"
    )


@app.route(
    "/login",
    methods=["GET", "POST"]
)
def login():

    authenticated = None
    backend_response = None

    if request.method == "POST":

        username = request.form["username"]

        result = authenticate_user(
            username
        )

        print("\n====================")
        print("AUTH RESULT")
        print("====================")
        print(result)
        print("====================\n")

        backend_response = result

        authenticated = result.get(
            "authenticated",
            False
        )

    return render_template(
        "login.html",
        authenticated=authenticated,
        backend_response=backend_response
    )


@app.route("/dashboard")
def dashboard():

    stats = get_stats()

    return render_template(
        "dashboard.html",
        stats=stats
    )


@app.route(
    "/prime-test",
    methods=["GET", "POST"]
)
def prime_testing():

    result = None

    if request.method == "POST":

        number = int(
            request.form["number"]
        )

        result = prime_test(
            number
        )

    return render_template(
        "prime_test.html",
        result=result
    )


@app.route("/analytics")
def analytics():

    stats = get_stats()

    carmichael = run_carmichael_demo()

    benchmark = benchmark_number(561)

    return render_template(
        "analytics.html",
        stats=stats,
        carmichael=carmichael,
        benchmark=benchmark
    )


if __name__ == "__main__":

    app.run(
        host="0.0.0.0",
        port=5000,
        debug=True
    )