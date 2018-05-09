import os
import re
import pandas as pd
import librosa

from feature_extraction import FeatureExtraction


class DataPreparation:
    def __init__(self, audio_path, dataset_save_file):
        self.audio_path = audio_path
        self.dataset_save_file = dataset_save_file
        pass

    def prepare_data(self):
        regex_path = re.compile(r'^[0-9]')
        audio_dir_path = [i for i in os.listdir(self.audio_path) if regex_path.match(i)]

        regex_file = re.compile(r'.*[wav|ogg]$')
        dataset = pd.DataFrame()
        labels = []

        for directory in audio_dir_path:

            feature_extraction = FeatureExtraction(label=directory)
            file_list = [i for i in os.listdir(os.path.join(self.audio_path, directory)) if regex_file.match(i)]

            for audio_file in file_list:
                audio_file_abspath = os.path.join(self.audio_path, directory, audio_file)

                audio_data, sr = librosa.load(audio_file_abspath, sr=44100, mono=True, duration=5)
                features, label = feature_extraction.extract_feature(audio_data)

                dataset = dataset.append(pd.Series(features), ignore_index=True)
                labels.append(label)

        label_df = pd.DataFrame(labels, columns=['label'])
        dataset = pd.concat([dataset, label_df], axis=1)
        dataset.to_csv(self.dataset_save_file, sep=",", index=False, encoding="utf8")
