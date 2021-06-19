# mzserver
Web server in C.

# Requirements
Docker installed on host machine.

# Installation
- Clone repo locally.

# Usage
- Inside the cloned repo do the following
- `make container-server`
- In a web browser on host, enter: `http://localhost:8080/index.html`
- Notice request print in terminal and `"Hello world!"` response in browser.
- To exit server, in separate terminal run 
`docker container stop <container id>`