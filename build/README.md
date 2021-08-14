# Build

Here are some instructions on how to build the static e-maxx-eng website.

```bash
cd e-maxx-eng
docker build -f build/Dockerfile . -t e-maxx-eng-builder
mkdir public
docker run -v $PWD/public:/output -e BASEURL="$PWD/public/" e-maxx-eng-builder:latest
```
`/output` is the directory where the Docker container will export the files to.
The `BASEURL` is the base of all urls.
If you want to test it locally, e.g. you can set it `BASEURL=$PWD/public`, if you want to test it with Firebase (`firebase emulators:start`), use `BASEURL="http://localhost:5000"`, or if you want to deploy it to [https://cp-algorithms.com](https://cp-algorithms.com), use `BASEURL="https://cp-algorithms.com"`.
