#!/bin/bash


PYTHON_EXEC=${HOME}/anaconda3/bin/python

rm -r build/ dist/ pyrserpp_LEANDRO.egg-info/

${PYTHON_EXEC} setup.py sdist bdist_wheel
#${HOME}/anaconda3/bin/python -m pip uninstall pyrserpp
${HOME}/anaconda3/bin/pip install .

