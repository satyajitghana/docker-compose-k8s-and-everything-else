# KrishiAI - Server

---

## Instructions to run on docker-compose

```bash
docker-compose up
```

---

## Instructions to run on Kubernetes

Make sure to build the Dockerfile images before running kubernetes

convert the `docker-compose.yaml` to `kubemanifests.yaml` using `kompose`

```bash
kompose convert -f docker-compose.yaml -o kubemanifests.yaml
```

change api version for Deployment to 

```yaml
- apiVersion: apps/v1
  kind: Deployment
```

or run `sed -i 's|extensions/v1beta1|apps/v1|g' kubemanifests.yaml`

add `selector` to the `Deployment` pods

```yaml
  spec:
    replicas: 1
    strategy: {}
    selector:
      matchLabels:
        io.kompose.service: krishiai-web
```

add `LoadBalancer` type to Service to expose the ports into `localhost`

```yaml
  spec:
    type: LoadBalancer
    ports:
    - name: "80"
      port: 80
      targetPort: 3000
```

add `imagePullPolicy` to never pull images, so we can run it on localhost

```yaml
          image: krishiai_model:latest
          imagePullPolicy: Never
          name: tfserving
```

set the `SERVING_HOSTNAME` environment variable as

```yaml
      spec:
        containers:
        - env:
          - name: SERVING_HOSTNAME
            value: krishiai-tfserving
```

change the number of replicas as desired

```yaml
  spec:
    replicas: 5
    strategy: {}
```

### Run the pods

```bash
kubectl apply -f kubemanifests.yaml      
```

### View the pods

```bash
kubectl get all
```

Stop the pods
```bash
kubectl delete -f kubemanifests.yaml      
```

## Instructions to run weavescope

```bash
kubectl apply -f scope.yaml
```

expose port 4040 to localhost
```bash
kubectl port-forward -n weave "$(kubectl get -n weave pod --selector=weave-scope-component=app -o jsonpath='{.items..metadata.name}')" 4040
```

open `http://localhost:4040/`

## Instructions to run Kubernetes Dashboard
(a little tedious)

apply the config file
```bash
kubectl apply -f kubedashboard.yaml
```

generate a admin-account and get the token

```bash
$ kubectl create serviceaccount krishiadmin -n default
$ kubectl create clusterrolebinding krishi-admin -n default --clusterrole=cluster-admin --serviceaccount=default:krishiadmin
$ kubectl get secret $(kubectl get serviceaccount krishiadmin -o jsonpath="{.secrets[0].name}") -o jsonpath="{.data.token}" | base64 --decode
```

run the proxy
```bash
kubectl proxy
```

now go to `http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/ and enter the token

to stop the dashboard
```bash
$ kubectl delete -f kubedashboard.yaml
```
