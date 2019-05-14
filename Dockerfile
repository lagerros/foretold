FROM node:12.2.0

RUN env

COPY package.json /opt/app/
COPY yarn.lock /opt/app/
COPY lerna.json /opt/app/
COPY packages /opt/app/packages/
WORKDIR /opt/app

RUN yarn install --loglevel=warn --unsafe-perm --ignore-scripts
RUN yarn run bootstrap

EXPOSE ${PORT:-80}

