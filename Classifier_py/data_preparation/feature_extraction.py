import pandas as pd
import numpy as np
import librosa.feature as lrf
import audio_utils


class FeatureExtraction:
    RATE = 44100
    FRAME = 512

    def __init__(self, label=None):
        if label is None:
            self.label = ''
        else:
            self.label = label

    def extract_feature(self, audio_data):
        """
        extract features from audio data
        :param audio_data:
        :return:
        """

        zcr = lrf.zero_crossing_rate(audio_data, frame_length=self.FRAME, hop_length=self.FRAME / 2)
        feature_zcr = np.mean(zcr)

        ste = audio_utils.AudioUtils.ste(audio_data, 'hamming', int(20 * 0.001 * self.RATE))
        feature_ste = np.mean(ste)

        ste_acc = np.diff(ste)
        feature_steacc = np.mean(ste_acc[ste_acc > 0])

        stzcr = audio_utils.AudioUtils.stzcr(audio_data, 'hamming', int(20 * 0.001 * self.RATE))
        feature_stezcr = np.mean(stzcr)

        mfcc = lrf.mfcc(y=audio_data, sr=self.RATE, n_mfcc=13)
        feature_mfcc = np.mean(mfcc, axis=1)

        spectral_centroid = lrf.spectral_centroid(y=audio_data, sr=self.RATE, hop_length=self.FRAME / 2)
        feature_spectral_centroid = np.mean(spectral_centroid)

        spectral_bandwidth = lrf.spectral_bandwidth(y=audio_data, sr=self.RATE, hop_length=self.FRAME / 2)
        feature_spectral_bandwidth = np.mean(spectral_bandwidth)

        spectral_rolloff = lrf.spectral_rolloff(y=audio_data, sr=self.RATE, hop_length=self.FRAME / 2,
                                                roll_percent=0.90)
        feature_spectral_rolloff = np.mean(spectral_rolloff)

        spectral_flatness = lrf.spectral_flatness(y=audio_data, hop_length=self.FRAME / 2)
        feature_spectral_flatness = np.mean(spectral_flatness)

        features = np.append([feature_zcr, feature_ste, feature_steacc, feature_stezcr, feature_spectral_centroid,
                              feature_spectral_bandwidth, feature_spectral_rolloff, feature_spectral_flatness],
                             feature_mfcc)
        return features, self.label
