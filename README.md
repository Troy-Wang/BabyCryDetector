# BabyCryDetector

## Background

This is a project I finished during my internship in Intel Labs China (2012.12.01-2013.05.31). 
Aiming to detect baby's cry, this project became one part of Nursery 2.0, which was built in Edison and demonstrated at [CES2014](https://www.theverge.com/2014/1/6/5282472/intel-announces-edison-a-computer-the-size-of-an-sd-card).

## Introduction

1. **Monitor_matlab** is a Matlab-based baby cry detector. The *BabyCryDetectorReport.pdf* illustrates the implementation details. Run *Monitor.m* to start.

2. **Monitor_c** is a C-based baby cry detector, totally written according to the matlab codes. Instead of monitoring the environment voice, it simply reads voice data from files. Run *AMain.c* to start.

3. The two preceding modules were all finished in late 2012, at which time Machine Learning was not that popular as today. And I had very few baby cry samples/instances then. So the classifier of the monitor is very simple, just decide by judging the extracted feature values. For example, check whether the average frequency is bigger than 1000 or not. **Classifier_py** is a Python-based baby cry classifier. I get more samples on the Internet, extract features, and build several classifiers with Scikit-Learn.
