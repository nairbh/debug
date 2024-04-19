#!/usr/bin/python3
""" This module defines the API routes to index.

Routes:
    /status: Return JSON status --> 'OK'.
    /stats: Return a list of the sum of all objects by type.
"""
from api.v1.views import app_views
from flask import jsonify


@app_views.route("/status", methods=['GET'], strict_slashes=False)
def status():
    """ Endpoint that return JSON status: OK."""
    return jsonify({'status': 'OK'})


@app_views.route("/stats")
def stats():
    """ Endpoint that return a list of the number of each objects by type """
    from models import storage
    from models.amenity import Amenity
    from models.city import City
    from models.place import Place
    from models.user import User
    from models.review import Review
    from models.state import State
    objs = {
        "amenities": storage.count(Amenity),
        "cities": storage.count(City),
        "places": storage.count(Place),
        "users": storage.count(User),
        "reviews": storage.count(Review),
        "states": storage.count(State)
    }
    return jsonify(objs)
