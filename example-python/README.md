# Python Docker

## Build

```bash
docker build -t hello-fastapi .
```

## Run

```bash
docker run -it --rm -p 8000:8000 hello-fastapi
```

Open http://localhost:8000/cat in your browser.