#!/bin/sh

#Check 'docker' and 'minikube' are installed
if ! which docker >/dev/null 2>&1 ||
    ! which minikube >/dev/null 2>&1
then
    echo "Please install Docker and Minikube"
    exit 1
fi

#Check 'delete' and 'update' option if has parameter
if [ "$1" = "delete" ]
then
    kubectl delete -k srcs
elif [ "$1" = "apply" ]
then
    kubectl apply -k srcs
else
    #UNCOMMENT ON 42 CLUSTER FOR STORAGE (NEEDS MODIFY)
    # export MINIKUBE_HOME="/sgoinfre/goinfre/Perso/eunhkim/ft_service/minikube/"

    #Setup minikube apiserver with x1.5 SPEC for safety working
    minikube start --vm-driver=virtualbox \
        --cpus 3 --disk-size=30000mb --memory=3000 \
		--extra-config=apiserver.service-node-port-range=1-31000

    #Enable addons
    minikube addons enable ingress
    minikube addons enable metrics-server

    #Update dump file to target file with IP
    export MINIKUBE_IP=$(minikube ip)
    cp -f srcs/ftps/vsftpd_sub.conf srcs/ftps/vsftpd.conf
    sed -i '' "s/##MINIKUBE_IP##/$MINIKUBE_IP/g" srcs/ftps/vsftpd.conf
    cp srcs/wordpress/wordpress_dump.sql srcs/wordpress/wordpress_dump-target.sql
    sed -i '' "s/##MINIKUBE_IP##/$MINIKUBE_IP/g" srcs/wordpress/wordpress_dump-target.sql
    cp srcs/telegraf/telegraf.conf srcs/telegraf/telegraf-target.conf
    sed -i '' "s/##MINIKUBE_IP##/$MINIKUBE_IP/g" srcs/telegraf/telegraf-target.conf

    #Build images on minikube docker
    eval $(minikube docker-env)
    docker build -t ft_nginx srcs/nginx
    docker build -t ft_ftps srcs/ftps
	docker build -t ft_mysql srcs/mysql
    docker build -t ft_phpmyadmin srcs/phpmyadmin
    docker build -t ft_wordpress srcs/wordpress
    docker build -t ft_grafana srcs/grafana

    #Apply all .yaml files in srcs directory
    kubectl apply -k srcs
fi
