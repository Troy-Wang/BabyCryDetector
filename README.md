# BabyCryDetector

## Background

This is a project I finished during my internship in Intel Labs China (2012.12.01-2013.05.31). 
Aiming to detect baby's cry, this project became one part of Nursery 2.0, which was built in Edison and demonstrated at [CES2014](https://www.theverge.com/2014/1/6/5282472/intel-announces-edison-a-computer-the-size-of-an-sd-card).

## Introduction

1. **Monitor_matlab** is a Matlab-based baby cry detector. The *BabyCryDetectorReport.pdf* illustrates the implementation details. Run *Monitor.m* to start.

2. **Monitor_c** is a C-based baby cry detector, totally written according to the matlab codes. Instead of monitoring the environment voice, it simply reads voice data from files. Run *AMain.c* to start.

3. The two preceding modules were all finished in late 2012, at which time Machine Learning was not that popular as today. And I had very few baby cry samples/instances then. So the classifier of the monitor is very simple, just decide by judging the extracted feature values. For example, check whether the average frequency is bigger than 1000 or not. **Classifier_py** is a Python-based baby cry classifier. I get more samples on the Internet, extract features, and build several classifiers with Scikit-Learn.

## Newly Updated: Classifier with Python

Due to the prosperity of Machine Learning, I'm considering reconstructing this project with sklearn. So here is the python version. I searched on Github before started, [giulbia's work](https://github.com/giulbia/baby_cry_detection) is pretty good. I use her dataset and do some more work here.

Key python libs: **sklearn, librosa, pandas, numpy, scipy**

Whole system consists of three modules: 
- **data_preparation** for feature extraction and training data preparation 
- **model_training** for models training with sklearn
- **predictor** for audio-prediction with generated models

## Details for *Monitor\_matlab* and *Monitor\_c*
### Flowchart

![flowchart](https://github.com/Troy-Wang/BabyCryDetector/raw/master/imgs/flowchart.png)

### System Structure
![flowchart](https://github.com/Troy-Wang/BabyCryDetector/raw/master/imgs/structure.png)

### Tool functions

#### enframe

- Split the voice data into frames
- Input:original voice data,frame length,frame shift/increment,
- Output:arrays of frames


#### clipping

- Pre-processing function for audio signals, there’re two common clipping method: center clipping and 3-level clipping. Pitch frequency calculation can be accelerated by 10 times after clipping.- Input:original voice data,clipping method (center or 3-level)- Output:clipped voice data#### FIR

- FIR low pass filter.
- Since human voice (include baby cry) frequency is always below 3000Hz, we only care about those voice signals going through a low pass filter with a cutoff frequency of 3000Hz. This is why the sampling frequency of the phone is 8KHz.
- Input:original voice data,cutoff frequency
- Output:filtered voice data

#### linsmooth

- A linear smoothing function to eliminate the ‘wild points’ of a dataset.
- In our system, we use another kind of smoothing method called median smoothing due to their efficiency. They can also be combined to form other smoothing methods. I didn’t do a result-accuracy experiment on this smoothing thing, so this linear smoothing function is still provided here for future work, research or optimization.
- Input:original dataset,smoothing window length,Window type (hanmming as default)
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
- Input:original voice data,frame length,frame shift/increment,

- Output:voice activity start point,voice activity end point#### zcro

- Function for zero-crossing rate calculation.
- This function is used to calculate the zero-crossing rate of each signal frame.
- Input:voice frames
- Output:zero-crossing ratio of each frame

### Features

Names of the feature extraction functions in this system all start with a capital letter. They have the same input, and one feature-value as output (the STE has two feature-values).They are:
- **Freq** :	For frequency-related feature extraction- **PitchFreq**:	For pitch-frequency-related feature 			extraction- **STE**:	For short-time-energy-related feature 		extraction- **ZCR**:	For zero-crossing-ratio-related feature 			extraction
Input:
- original voice data- sampling frequency of the voice signal (In the monitor module, we record with a frequency of 8KHz)- sampling bits of the voice signalOutput:one or two value/values for the corresponding feature

#### Frequency

- Human voice is mainly made up of the frequency range from 85Hz ~ 255Hz. Sometimes the soprano can arrive 700-1000Hz. For baby cry, the most of the voice stays over 1000Hz. - Use frequency spectrum to see the distribution of the voice frequency.- We want a value that can illustrate in which frequency band the voice data mostly stay. For all frequency whose magnitude > 0.25*magnitude , we get a value:
![](http://latex.codecogs.com/gif.latex?\\frac{\\sum{freq_n*mag_n}}{\\sum{mag_n}})


#### Short-Time Energy

- Energy of 浊音 signals is much bigger than that of 清音 signals. A Baby’s cry is usually the former one.- This feature is not so important, because adults can produce 浊音 with very high energy. And baby cry’s energy is not so high sometimes.### Max STE Acceleration

- Due to the burst of the baby cry, the STE of the cry signal can arrive a very high value in just one or two frames.

- Here are the max-accs of 20 baby cry samples. Some baby cry samples have a low value of max-acc because the cry is very smooth.61.024533
34.521525327.117388349.730113493.107778348.707116426.581542626.655594292.484589213.7207431.01904912.46664315.48389796.94944347.65147216.93026581.86182217.52430857.89369


- Here are the max-accs of 5 adult voice samples. Some adult voice samples have a high value of max-acc because of the instantaneous bursts.
7.852295
333.188928
4.116091
12.796357
17.882019
49.823669
41.898621#### Pitch Frequency

- Pitch Frequency is one of the most important feature of human voice. For ref, [PitchDetectionAlgorithm](http://en.wikipedia.org/wiki/Pitch_detection_algorithm)- The fundamental frequency of speech can vary from 40 Hz for low-pitched male voices to 600 Hz for children or high-pitched female voices.- As I mentioned in the previous page, we use 3-level clipping to reduce the calculation of pitch frequency.- After clipping, we use short-time-autocorrelation methods to calculate the pitch frequency of each frame. Autocorrelation methods need at least two pitch periods to detect pitch. This means that in order to detect a fundamental frequency of 40 Hz, at least 50 milliseconds (ms) of the speech signal must be analyzed. In this system, we use 30ms as a frame for analyze.
- Pitch frequency estimation. For example, if the first pitch of the frame arrives at about 50, the pitch frequency of this frame is (8000/50=160Hz), 8000 is the sampling frequency of the voice signal.For every frame, we must discard the first several samples due to signal disturbance. In this system, I discard the samples of the first 10% of each frame, that is 3ms\*8KHz=24 samples.- After getting the pitch of the frame, we need another test. If the pitch value is smaller than 0.25\*STE-of-this-frame, then we consider this frame as 清音, and set its pitch frequency to 0.
- Post-processing. As I mentioned in the previous page, after getting the pitch frequency of each frame, we’d better do a smoothing work to eliminate the wild points.
- For this feature, what we care about is, how many frames of the voice signal arrive a pitch frequency over 200.In this system, if more than 5 frames of the voice signal arrive a frequency over 200, then this voice has a higher possibility to be a baby cry.

#### Zero-crossing rate

- The zero-crossing rate is the rate of sign-changes along a signal, i.e., the rate at which the signal changes from positive to negative or back.
- For human voices, those who have higher values of zero-crossing rate tend to be baby cry voices. In this system, we set the boundary to be 50. Of course, this can be accurately determined by more samples and experiments.

### Other features
For future work, research or optimization, the follow feature can be added to the system.
- Harmonicity Factor- Harmonic-to-Average Power Ratio (HAPR)- Burst Frequency### Classify

I intended to design a classifier (decision tree, KNN or something like that), but there’s not so many instances. In the future work, if many more baby cry wav files or samples are given, we can build a much more accurate classifier for this system instead of just several ‘if’ clauses.

### Monitor

The monitor monitors the voice activities in the environment. When a voice with a volume over 0.4, the system will start to record for 15ms(0.4 and 15ms can be set manually). Then the voice recorded will be sent to the above-mentioned feature extraction functions to be classified as a-baby-cry or not-a-baby-cry.
For matlab code, the monitor uses [Analog Input](http://www.mathworks.cn/cn/help/daq/examples/continuous-acquisition-using-analog-input.html) (Now deprecated, please use [audiorecorder](https://ww2.mathworks.cn/help/matlab/ref/audiorecorder.html?lang=en) instead). For matlab code, the real-time voice waveform is shown in a figure.

### What can be improved

- **Clipping method**:  Some other clipping methods can be tested to see which is the best, in both efficiency and accuracy aspects.- **Smoothing method**: Some other smoothing methods can be tested to see which is the best, in both efficiency and accuracy aspects.- **Feature selection**: More voice signal features can be added to the system for classification. As mentioned in page 23.- **Parameters**: Some parameters can be set more accurately with more experiments, like threshold for recording, frame length for every feature extraction, pitch frequency cutoff boundary………- **Classifier**: Since the baby cry instances is really limited, we’ve no need to design a classifier like decision tree, KNN or svm. For future work, we can build an accurate classifier for classification (baby cry or not) using those extracted features.- There are really lots of choices for every step, I’ve done much to optimize the efficiency and the accuracy, but I’m not so sure if there is some other methods which take both efficiency and accuracy into consideration and can do a better job. So, I think there’s really much more we can do in the future.