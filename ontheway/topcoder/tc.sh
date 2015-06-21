#!/bin/bash

# required for xmonad
export _JAVA_AWT_WM_NONREPARENTING=1
javaws -Xms512m -Xmx2g ContestAppletProd.jnlp
