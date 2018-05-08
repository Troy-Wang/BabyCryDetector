# BabyCryDetector

## Background

This is a project I finished during my internship in Intel Labs China (2012.12.01-2013.05.31). 
Aiming to detect baby's cry, this project became one part of Nursery 2.0, which was built in Edison and demonstrated at [CES2014](https://www.theverge.com/2014/1/6/5282472/intel-announces-edison-a-computer-the-size-of-an-sd-card).

## Introduction

1. **Monitor_matlab** is a Matlab-based baby cry detector. The *BabyCryDetectorReport.pdf* illustrates the implementation details. Run *Monitor.m* to start.

2. **Monitor_c** is a C-based baby cry detector, totally written according to the matlab codes. Instead of monitoring the environment voice, it simply reads voice data from files. Run *AMain.c* to start.

3. The two preceding modules were all finished in late 2012, at which time Machine Learning was not that popular as today. And I had very few baby cry samples/instances then. So the classifier of the monitor is very simple, just decide by judging the extracted feature values. For example, check whether the average frequency is bigger than 1000 or not. **Classifier_py** is a Python-based baby cry classifier. I get more samples on the Internet, extract features, and build several classifiers with Scikit-Learn.

## Flowchart

![flowchart](https://github.com/Troy-Wang/BabyCryDetector/raw/master/imgs/flowchart.png)

## System Structure
![flowchart](https://github.com/Troy-Wang/BabyCryDetector/raw/master/imgs/structure.png)

## Tool functions

#### enframe

- Split the voice data into frames
- Input:original voice dataframe lengthframe shift/increment
- Output:arrays of frames


#### clipping

- Pre-processing function for audio signals, there’re two common clipping method: center clipping and 3-level clipping. Pitch frequency calculation can be accelerated by 10 times after clipping.- Input:original voice dataclipping method (center or 3-level)- Output:clipped voice data#### FIR

- FIR low pass filter.
- Since human voice (include baby cry) frequency is always below 3000Hz, we only care about those voice signals going through a low pass filter with a cutoff frequency of 3000Hz. This is why the sampling frequency of the phone is 8KHz.
- Input:original voice datacutoff frequency
- Output:filtered voice data

#### linsmooth

- A linear smoothing function to eliminate the ‘wild points’ of a dataset.
- In our system, we use another kind of smoothing method called median smoothing due to their efficiency. They can also be combined to form other smoothing methods. I didn’t do a result-accuracy experiment on this smoothing thing, so this linear smoothing function is still provided here for future work, research or optimization.
- Input:original datasetsmoothing window lengthWindow type (hanmming as default)
- Output:smoothed dataset

#### smoothing

- Post-processing function for pitch frequency feature extraction.
- Use this smoothing function to eliminate the wild points.
- In detail, I use the composition of 3-point median smoothing method and 5-point median smoothing method.
- Input:original pitch frequency dataset
- Output:smoothed pitch frequency dataset

#### vad

- Voice Activity Detection (Endpoint detection) function
- This function is used to find the start point and the end point of the voice signal.
- I don’t use this in this system, but still provided here in case of future work ,research or optimization.
- Input:original voice dataframe lengthframe shift/increment

- Output:voice activity start pointvoice activity end point#### zcro

- Function for zero-crossing rate calculation.
- This function is used to calculate the zero-crossing rate of each signal frame.
- Input:voice frames
- Output:zero-crossing ratio of each frame
