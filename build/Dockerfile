FROM python:3.9-slim

WORKDIR /app/

COPY build/requirements.txt .
RUN pip install -r requirements.txt

COPY build/main.py main.py

ENV BASEURL="https://cp-algorithms.com"
VOLUME /input
VOLUME /output

CMD python main.py -i /input/src -o /output --template-dir /input/src/_templates --static-dir /input/static --baseurl $BASEURL
