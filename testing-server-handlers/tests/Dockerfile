FROM python:3.9


WORKDIR /app
COPY requirements.txt .
COPY all .

RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt

CMD pytest test_shoot.py && pytest test_repair.py
#CMD ["pytest", "test_shoot.py", "test_repair.py"]
