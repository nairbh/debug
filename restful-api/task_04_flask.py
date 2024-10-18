#!/usr/bin/env python3
"""module creates a simple API"""

from flask import Flask
from flask import jsonify
from flask import request

app = Flask(__name__)


@app.route("/")
def home():
    return "Welcome to the Flask API!"


@app.route("/data")
def showdata():
    return jsonify(users)


@app.route("/status")
def status():
    return jsonify("OK"), 200


@app.route("/users/<username>")
def get_user(username):
    if username in users:
        return jsonify(users[username])
    else:
        return jsonify({"Error": "user not found"}), 404


@app.route("/add_user", methods=["POST"])
def add_user():
    if request.is_json:
        data = request.get_json()
        username = data.get("username")
        if username and username not in users:
            users[username] = {
                "name": data.get("name"),
                "age": data.get("age"),
                "city": data.get("city")
            }
            return jsonify(
                {"User added", users[username]}), 201
        else:
            return jsonify(
                {"error": "Invalid data or user already exists"}), 400
    else:
        return jsonify({"error": "Request must be JSON"}), 400


if __name__ == "__main__":
    app.run()
