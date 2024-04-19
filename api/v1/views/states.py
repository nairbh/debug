#!/usr/bin/python3
""" This module defines the API routes to states.

Routes:
    [GET]:
        /states/: Return all States.
        /states/<state_id>: Return the State if exist or 404.

    [POST]:
        /states: Creates new state.

    [DELETE]:
        /states/<state_id>: Delete state if exist or 404.

    [PUT]:
        /states/<state_id>: Modify state if exist or 404.
"""
from api.v1.views import app_views
from flask import jsonify, abort, make_response, request
from models import storage
from models.state import State


@app_views.route('/states', methods=['GET'], strict_slashes=False)
def states():
    """Retrieve a list of all State objects"""
    states = storage.all(State)  # recupère tous les objets de type State
    state_list = []  # cree une liste vide
    for state in states.values():
        # convertie en dictionnaire qui est ajouté a la liste
        state_list.append(state.to_dict())
    return jsonify(state_list)  # return la list convertie en dictionnaire json


@app_views.route('/states/<state_id>', methods=['GET'], strict_slashes=False)
def get_states(state_id):
    """Retrieve a State object by ID"""
    state = storage.get(State, state_id)
    if state is None:
        abort(404)  # Abandonne la requête avec une erreur 404
    return jsonify(state.to_dict())


@app_views.route('/states/<state_id>', methods=['DELETE'],
                 strict_slashes=False)
def delete_state(state_id):
    """Delete a State object by ID"""
    state = storage.get(State, state_id)
    if state is None:
        abort(404)

    # Supprimer l'objet State de la base de données
    storage.delete(state)
    storage.save()

    return make_response(jsonify({}), 200) # retourne un dictionnaire vide et un code 200


@app_views.route('/states', methods=['POST'], strict_slashes=False)
def creates_state():
    """ Create instance of state. """
    # Get JSON data of the body request sent by POST.
    req_json = request.get_json()
    # Check if Data is not none and had name.
    if not request.get_json():
        return make_response(jsonify({"error": "Not a JSON"}), 400)
    if "name" not in request.get_json():
        return make_response(jsonify({"error": "Missing name"}), 400)
    new_state = State()
    # Loops to set each key:value to the new state.
    for (key, value) in req_json.items():
        setattr(new_state, key, value)
    # Save Data.
    storage.new(new_state)
    storage.save()
    return make_response(jsonify(new_state.to_dict()), 201)


@app_views.route('/states/<state_id>', methods=['PUT'], strict_slashes=False)
def update_state(state_id):
    """ Modify instance of state if exist, else raise 404. """
    target_state = storage.get(State, state_id)
    # Check if object exist.
    if target_state is None:
        return make_response(jsonify({"error": "Not found"}), 404)
    body_json = request.get_json()
    if body_json is None:
        return make_response(jsonify({"error": "Not a JSON"}), 400)
    # Loops to update each key:value to the state.
    for (key, value) in body_json.items():
        setattr(target_state, key, value)
    # Save Data
    target_state.save()
    return make_response(jsonify(target_state.to_dict()), 200)
    