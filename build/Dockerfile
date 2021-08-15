FROM python:3.9-slim

WORKDIR /app/

COPY build/requirements.txt .
RUN pip install -r requirements.txt

COPY . .

ENV BASEURL="https://cp-algorithms.com"
VOLUME /output

CMD python build/build.py -i src -o /output --template-dir src/_templates --static-dir static --baseurl $BASEURL
