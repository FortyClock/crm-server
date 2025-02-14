FROM python:3.9


WORKDIR /app
COPY requirements.txt .
COPY tests.py .


RUN pip install --no-cache-dir requirements.txt

CMD ["pytest", "tests.py"]
