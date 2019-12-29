# Linux daemon Template

A daemon is a computer program that runs as a background process, rather than being under the direct control of an interactive user. Traditionally, the process names of a daemon end with the letter d, for clarification that the process is in fact a daemon, and for differentiation between a daemon and a normal computer program.


## New Style Daemons

Modern services for Linux should be implemented as new-style daemons. This makes it easier to supervise and control them at runtime and simplifies their implementation.

For developing a new-style daemon, none of the initialization steps recommended for SysV daemons need to be implemented. New-style init systems such as systemd make all of them redundant. Moreover, since some of these steps interfere with process monitoring, file descriptor passing and other functionality of the init system, it is recommended not to execute them when run as new-style service.

Note that new-style init systems guarantee execution of daemon processes in a clean process context: it is guaranteed that the environment block is sanitized, that the signal handlers and mask is reset and that no left-over file descriptors are passed. Daemons will be executed in their own session, with standard input connected to /dev/null and standard output/error connected to the systemd-journald.service(8) logging service, unless otherwise configured. The umask is reset.

It is recommended for new-style daemons to implement the following:

- [x] If SIGTERM is received, shut down the daemon and exit cleanly.

- [ ] If SIGHUP is received, reload the configuration files, if this applies.

- [ ] Provide a correct exit code from the main daemon process, as this is used by the init system to detect service errors and problems. It is recommended to follow the exit code scheme as defined in the LSB recommendations for SysV init scripts.

- [ ] If possible and applicable, expose the daemon's control interface via the D-Bus IPC system and grab a bus name as last step of initialization.

- [ ] For integration in systemd, provide a .service unit file that carries information about starting, stopping and otherwise maintaining the daemon. See systemd.service(5) for details.

- [ ] As much as possible, rely on the init system's functionality to limit the access of the daemon to files, services and other resources, i.e. in the case of systemd, rely on systemd's resource limit control instead of implementing your own, rely on systemd's privilege dropping code instead of implementing it in the daemon, and similar. See systemd.exec(5) for the available controls.

- [ ] If D-Bus is used, make your daemon bus-activatable by supplying a D-Bus service activation configuration file. This has multiple advantages: your daemon may be started lazily on-demand; it may be started in parallel to other daemons requiring it — which maximizes parallelization and boot-up speed; your daemon can be restarted on failure without losing any bus requests, as the bus queues requests for activatable services. See below for details.

- [ ] If your daemon provides services to other local processes or remote clients via a socket, it should be made socket-activatable following the scheme pointed out below. Like D-Bus activation, this enables on-demand starting of services as well as it allows improved parallelization of service start-up. Also, for state-less protocols (such as syslog, DNS), a daemon implementing socket-based activation can be restarted without losing a single request. See below for details.

- [ ] If applicable, a daemon should notify the init system about startup completion or status updates via the sd_notify(3) interface.

- [ ] Instead of using the syslog() call to log directly to the system syslog service, a new-style daemon may choose to simply log to standard error via fprintf(), which is then forwarded to syslog by the init system. If log levels are necessary, these can be encoded by prefixing individual log lines with strings like "<4>" (for log level 4 "WARNING" in the syslog priority scheme), following a similar style as the Linux kernel's printk() level system. For details, see sd-daemon(3) and systemd.exec(5).

- [ ] As new-style daemons are invoked without a controlling TTY (but as their own session leaders) care should be taken to always specify `O_NOCTTY` on `open()` calls that possibly reference a TTY device node, so that no controlling TTY is accidentally acquired.

These recommendations are similar but not identical to the Apple MacOS X Daemon Requirements.

[Info Link](https://www.freedesktop.org/software/systemd/man/daemon.html#New-Style%20Daemons)


## Extra Information

Mistakes to avoid when designing Unix daemon programs

[Info Link](https://jdebp.eu/FGA/unix-daemon-design-mistakes-to-avoid.html)


## Dependencies

[libconfig++](https://hyperrealm.github.io/libconfig/)

How to install ubuntu 18.04 LTS.
```bash
sudo apt install libconfig++-dev
```

## How To Start

```bash
sudo systemctl start daemon-template

sudo systemctl stop daemon-template

sudo systemctl status daemon-template
```


