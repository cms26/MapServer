#!/usr/bin/env python3
import requests

url = 'http://localhost/map-items/'


def get_custom_items():
    jsonItems = requests.get(url).json()
    mapItems = []
    for item in jsonItems:
        if 'Custom-' in item['id']:
            mapItems.append(item)
    return mapItems


def put_data(update_data):
    print('Sending', update_data)
    requests.put(url, json=update_data)
