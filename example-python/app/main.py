import sys
import requests

from fastapi import FastAPI
from fastapi.responses import Response

version = f"{sys.version_info.major}.{sys.version_info.minor}"

app = FastAPI()


@app.get("/")
async def read_root():
    message = f"Hello world! From FastAPI running on Uvicorn with Gunicorn. Using Python {version}"
    return {"message": message}


@app.get("/cat")
async def read_cat():
    try:
        cat_api = "http://thecatapi.com/api/images/get?format=src"
        response = requests.get(cat_api)
        return Response(content=response.content, media_type=response.headers["content-type"])
    except:
        return {"message": "Error in fetching cat, Network request failed"}
