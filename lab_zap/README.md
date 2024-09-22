# ZAP Lab

## Prerequisite

- docker-compose, or a more recent docker runtime with `compose` command

Please note that this lab *requires a significant amount of local storage*, as creating the OWASP ZAP and DVWA images will consume approximately 2.5GB in total.

## Create the runtime environment

- Depending on your runtime, use either one of the following commands to bring up the service.

  ```
  docker-compose up -d
  docker compose up -d
  ```

  Once everything is up and running, connect to the ZAP Desktop UI via [http://localhost:8080/zap](http://localhost:8080/zap)

## Setup DVWA

You may need to setup DVWA before running the ZAP scanner. Please visit [http://localhost:4280/](http://localhost:4280/), login with username `admin` and password `password`, and click the **Create / Reset Database** in the **Setup DVWA** or **Setup / Reset DB** page.

## Run the automation testing plan

- Show the **Automation** Tab via the menu **View > Show Tab > Automation Tab**
- Load the pre-configured plan at `/home/zap/files/FullScanDvwaAuth.yaml`
- Click `Run Plan ...` -- It will scan vulnerabilities for the local [DVWA](https://github.com/digininja/DVWA) site
- Check the recognized vulnerabilities from the **Alerts** Tab.

Note that the `./files` directory is mapped into `/home/zap/files` in the runtime environment. You may need to set the permission of `./files` to be globally writable by running `chmod 777 ./files` to ensure that it is also writable in the docker runtime.

## Play with DVWA 

You can also try to play with the DVWA website by access its portal from [http://localhost:4280/login.php](http://localhost:4280/login.php). The default login credential is
```
admin
password
```

## Stop the runtime

Please remember to stop the runtime when you are done. The commands to stopping the runtime is:

```
docker-compose stop
docker compose stop
```

Replace `stop` with `start` if you plan to play with the lab again.

## Reset Everything

In case you need to cleanup and rebuild everything, please use the following instructions:

- Stop and remove existing containers:
  ```
  docker compose stop
  docker compose rm
  ```

- Remove the persistent storage
  ```
  docker volume rm lab_zap_dvwa
  ```
  You may use the command `docker volume ls` to confirm the name of the storage

- Rebuild the containers
  ```
  docker compose up -d
  ```

