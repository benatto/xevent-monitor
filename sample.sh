#!/bin/bash

###############################################################################
# XEvent-monitor hook script                                                  #
# This is a very simple sample to be executed when resolution change event    #
# (EventID = 333) is intercepted by XEvent-Monitor daemon.                    #
# The monitor will execute all scripts under:                                 #
#	/etc/xevent-monitor/events.d/<eventid>/                                   #
# once <eventid> found in XServer queue.				                      #
#                                                                             #
# Author: Marco A Benatto <benatto@mandriva.com.br                            #
###############################################################################

#DISPLAY=:0
#kdialog --msgbox "Resolution changed"

