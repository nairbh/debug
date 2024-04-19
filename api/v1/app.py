#!/usr/bin/python3
""" This module defines an API. """
from api.v1.views import app_views
from flask import Flask, jsonify, make_response
import os
from models import storage

app = Flask(__name__)
app.register_blueprint(app_views)


@app.teardown_appcontext
def close_session(self):
    """Remove the current SQLAlchemy session."""
    storage.close()


@app.errorhandler(404)
def not_found(self):
    """404 not found"""
    return make_response(jsonify({"error": "Not found"}), 404)


if __name__ == "__main__":
    host = os.getenv('HBNB_API_HOST', default="0.0.0.0")
    port = os.getenv('HBNB_API_PORT', default=5000)
    app.run(host=host, port=port, threaded=True)
