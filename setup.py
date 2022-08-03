#!/usr/bin/python
# -*- coding:utf-8 -*-
import os
import sys

from setuptools import setup

setup (
    name='PrivateServer',
    version='2.0',
    author='bckim',
    author_email='bckim@smilegate.com',
    description='Smilegate Ent (C) All right reservered.',
    install_requires=[
        'pypiwin32',
        'pymongo'
    ]
)
