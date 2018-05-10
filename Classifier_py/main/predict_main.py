from predictor.predictor import Predictor


def main():
    audio_file = './../data/audio/test_samples/30.wav'
    model_file = './../data/model/svm_model.pkl'

    predictor = Predictor(model_file)
    print predictor.predict(audio_file)


if __name__ == '__main__':
    main()
