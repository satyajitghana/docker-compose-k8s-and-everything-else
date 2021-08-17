# Chaos Testing using Litmus-Chaos

Supported Experiments

- Pod Delete
- Pod Network Latency
- Pod Network Loss
- Pod CPU Hog

## Running Chaos Test

please see instructions to install and setup litmus chaos before running experiments

```bash
kubectl apply -f pod-delete.yaml
```

## Instructions to install and setup litmus chaos

Install limus chaos
```bash
kubectl apply -f litmus-operator-v1.4.0.yaml
```

check if the pods are working
```bash
kubectl get pods -n litmus
```

OUTPUT
```
NAME                                 READY   STATUS              RESTARTS   AGE
chaos-operator-ce-7f8bb586f6-752s7   0/1     ContainerCreating   0          10s
```

check the CRDs
```bash
kubectl get crds | grep chaos   
```

OUTPUT
```
chaosengines.litmuschaos.io       2020-06-14T18:23:51Z
chaosexperiments.litmuschaos.io   2020-06-14T18:23:51Z
chaosresults.litmuschaos.io       2020-06-14T18:23:51Z
```

check api-resources
```bash
kubectl api-resources | grep chaos    
```

OUTPUT
```
chaosengines                                   litmuschaos.io                 true         ChaosEngine
chaosexperiments                               litmuschaos.io                 true         ChaosExperiment
chaosresults                                   litmuschaos.io                 true         ChaosResult
```

setup the experiments that can be used
```bash
kubectl apply -f experiments.yaml  
```

OUTPUT
```
chaosexperiment.litmuschaos.io/node-drain created
chaosexperiment.litmuschaos.io/disk-fill created
chaosexperiment.litmuschaos.io/pod-cpu-hog created
chaosexperiment.litmuschaos.io/pod-memory-hog created
chaosexperiment.litmuschaos.io/pod-network-corruption created
chaosexperiment.litmuschaos.io/pod-delete created
chaosexperiment.litmuschaos.io/pod-network-loss created
chaosexperiment.litmuschaos.io/disk-loss created
chaosexperiment.litmuschaos.io/pod-network-latency created
chaosexperiment.litmuschaos.io/node-cpu-hog created
chaosexperiment.litmuschaos.io/node-memory-hog created
chaosexperiment.litmuschaos.io/container-kill created
```

check if the experiments are installed
```bash
kubectl get chaosexperiments
```

OUTPUT
```
NAME                     AGE
container-kill           17s
disk-fill                17s
disk-loss                17s
node-cpu-hog             17s
node-drain               17s
node-memory-hog          17s
pod-cpu-hog              17s
pod-delete               17s
pod-memory-hog           17s
pod-network-corruption   17s
pod-network-latency      17s
pod-network-loss         17s
```

annotate your pod where we will run the experiments
```bash
kubectl annotate deploy/krishiai-web litmuschaos.io/chaos="true"
```

apply rbac
```bash
kubectl apply -f rbac.yaml
```

run the experiment
```bash
kubectl apply -f chaosengine.yaml
```


### NOTE

if your selector is
```yaml
    selector:
      matchLabels:
        io.kompose.service: krishiai-web
```

then in chaos engine use
```yaml
spec:
  appinfo:
    appns: 'default'
    applabel: 'io.kompose.service=krishiai-web'
    appkind: 'deployment'
```
to see app labels use `kubectl get pods --show-labels`

use weave to see the stats

```
kubectl port-forward -n weave "$(kubectl get -n weave pod --selector=weave-scope-component=app -o jsonpath='{.items..metadata.name}')" 4040
```