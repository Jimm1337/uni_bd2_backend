# Use a lightweight base image
FROM nginx:alpine

# Copy the static website files to the Nginx document root
COPY . /usr/share/nginx/html

# docker build -t my-frontend-image -f frontend.dockerfile .
# docker run -p 8080:80 --name my-frontend-container my-frontend-image
