cmake_minimum_required(VERSION 3.15)

# Define project name
project (mydaemon)

# Set up required subdirectories
add_subdirectory(daemon)

# Install the congfig file
install(FILES resource/config/daemon-template.conf DESTINATION /etc/daemon-template)

# Intall the systemd file
install(FILES resource/systemd/daemon-template.service DESTINATION /etc/systemd/system)

# Install the binary program
install(TARGETS daemon-template DESTINATION /usr/bin)