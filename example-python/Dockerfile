FROM tiangolo/uvicorn-gunicorn-fastapi:python3.8

ADD requirements.txt .

RUN pip install -r requirements.txt

EXPOSE 8000

COPY ./app /app

CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]