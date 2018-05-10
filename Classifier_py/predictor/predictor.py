import librosa
from sklearn.externals import joblib
from data_preparation.data_preparation import FeatureExtraction


class Predictor:
    def __init__(self, model):
        self.model = model
        self.my_model = joblib.load(self.model)

    def predict(self, audio_file):
        audio_data, sr = librosa.load(audio_file, sr=44100, mono=True)

        feature_extraction = FeatureExtraction()
        features, labels = feature_extraction.extract_feature(audio_data)

        return self.my_model.predict(features.reshape(1, -1))
