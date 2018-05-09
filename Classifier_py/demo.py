from data_preparation.data_preparation import DataPreparation

AUDIO_PATH = '/Users/troywang/Documents/ML/dataset'
DATASET_SAVE_FILE = './data/dataset/dataset.txt'
dp = DataPreparation(AUDIO_PATH, DATASET_SAVE_FILE)
dp.prepare_data()
