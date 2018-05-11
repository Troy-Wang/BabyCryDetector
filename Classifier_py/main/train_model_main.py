from model_training.model_training import ModelTraining
import pandas as pd
from sklearn.externals import joblib


def main():
    model_save_file = './../data/model/svm_model.pkl'
    data_save_file = './../data/dataset/dataset.txt'

    # model_save_file = './../data/model/rf_model.pkl'
    # data_save_file = './../data/dataset/dataset.txt'

    data = pd.read_csv(data_save_file, sep=',')
    X = data.iloc[:, range(21)]
    y = data['label']

    mt = ModelTraining(X, y)
    perf, model = mt.train_svm_model()

    print perf
    joblib.dump(model, model_save_file)


if __name__ == '__main__':
    main()
