#!/bin/bash

set -x

#getting HDMI input connection status
hdmi_status=$(cat /sys/class/drm/card0-HDMI-A-1/status)

if [ -f /home/usuario/.hdmistatus ]
then
	last_status=$(cat /home/usuario/.hdmistatus)
else
	last_status="disconnected"
fi

if [[ ${hdmi_status} = "connected" && ${last_status} = "disconnected" ]]
then
	echo "connected" > /home/usuario/.hdmistatus
	su - usuario -c "DISPLAY=:0 kdialog --yesno 'Deseja abrir suas configurações de áudio?'"
	dreturn=$?

	if [[ $dreturn -eq 0 ]]
	then
		su - usuario -c "DISPLAY=:0 gnome-volume-control -p hardware"
	fi
else
	if [[ ${hdmi_status} = "disconnected" ]]
	then
		echo "disconnected" > /home/usuario/.hdmistatus
	fi
fi
