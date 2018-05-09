import pandas as pd
import librosa as lr
import librosa.feature as lrf

audio_data, _ = lr.load('dataset/CryingBaby/1-22694-A.ogg', sr=44100)

print audio_data.shape

print lrf.zero_crossing_rate(audio_data)