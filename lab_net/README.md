# Networking Lab

This lab aims to practice setting up networking, NAT, port forwarding, and firewalls.

## Create the runtime environment

- Depending on your runtime, use either one of the following commands to bring up the service.

  ```
  docker-compose up -d
  docker compose up -d
  ```

## Network Topology

- There are five nodes in the network topology: gateway (gw), two clients in LAN (user1, user2), one web server in DMZ (web), and one outsider in WAN (outr).

- To avoid the side-effects caused by docker's networking design, we use VXLAN to create overlay networks for LAN and DMZ nodes. You have to complete the ***Basic Networking & Routing Setup*** first.

- The topology of the network is illustrated in the figure below.

  <img src="https://github.com/zoolab-org/clinic_lab/blob/main/lab_net/netopo.png?raw=true" width="50%" alt="Network Topology">

## Access to the Outsider via SSH

- If everything is brought up successfully, you should be able to access the outsider `outr` node using the ssh command:

    `ssh -p 30022 -i ./conf/ssh/id_ed25519 root@localhost`

- To interact with other nodes, you have to use the `docker exec` command:

  `docker exec -ti <labnet-node-name> bash`

  to access the interactive shell of each node.

## Basic Networking & Routing Setup

- Please read the `net-*.sh` scripts located in the `scripts` directory.

- You need to set up the VXLAN for all nodes except `outr`. The setup script for each node is summarized below.
    - Gateway (gw): `/scripts/net-gw.sh`. Please note that this script accepts an additional `<gateway-ip-address>` parameter. In case you find that the default route has a different prefix to the IP address of `eth0`, you may need to choose the default route address manually.
    - Client #1 (user1): `/scripts/net-user.sh 10.140.112.1`
    - Client #2 (user2): `/scripts/net-user.sh 10.140.112.2`
    - Web server (web): `/script/net-web.sh`

- Once you are done, you may try the following commands to test the correctness of your runtime.
    - Run `ping 10.140.113.254` from either `user1`, `user2`, or `web` should receive correct responses.
    - Run `ping 10.140.112.254` from either `user1`, `user2`, or `web` should receive correct responses.
    - Run `ping 10.140.113.100` from either `user1`, `user2`, or `gw`  should receive correct responses.
    - Run `ping 10.140.112.1` from either `user1`, `web`, or `gw`  should receive correct responses.
    - Run `ping 10.140.112.2` from either `user2`, `web`, or `gw`  should receive correct responses.

## NAT Setup

- Your job is to ensure that `user1` and `user2` can access the Internet.

- Try to configure the `gw` to achieve the goal.

- All you need is to manipulate the `nat` table using the `iptables` command on the `gw` node.

- Once you are done, use `ping 8.8.8.8` command in either `user1` or `user2` node to confirm the correctness of your setup.

## Port Forwarding Setup

- Your job is to ensure that `outr` can visit the `web` server placed in the DMZ.

- Try to configure the `gw` to achieve the goal.

- All you need is to manipulate the `nat` table using the `iptables` command on the `gw` node.

- Once the configuration is done, run the command `curl gw` in the `outr` node, and you should see a cute cat looking at you!

- You may also access the web server using your browser. Try to visit the link at [http://localhsot:30080/](http://localhsot:30080/). Note that it may not work for Docker Desktop running on Mac OS X.

- Alternatively, you may create an SSH tunnel to access the website from your browser. The tunnel can be created using the command:

  `ssh -p 30022 -i ./conf/ssh/id_ed25519 root@localhost -L 20080:gw:80 -L 20443:gw:443`

  Once the tunnel has been created, you can access the website from your desktop browser via the link at [http://localhsot:20080/](http://localhsot:20080/).

## Firewall Setup

- Your job is to ensure that everyone can access the `web` server in the DMZ, but the `web` server cannot access other nodes in the LAN.

- Try to configure the `gw` to achieve the goal.

- Once you are done, run `ping 10.140.112.1` from the `web` node, and you should ***NOT*** receive any response.

## HTTPS

- Your job is to run the HTTPS version of the website in the `web` server.

- To prevent you from breaking existing HTTP configuration, you may run another `nginx` instance configured to serve only HTTPS requests on port 443.

- Once the HTTPS server is up, browse your HTTPS website to ensure that the certificate is correctly loaded.

- Try to install the CA certificate in your browser (or OS) to ensure that your browser can automatically validate the web server's certificate.

- DO NOT forget to remove the CA certificate used for labs from your browser (and OS)

