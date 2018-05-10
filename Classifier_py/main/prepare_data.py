from data_preparation.data_preparation import DataPreparation


def main():
    audio_path = './../data/audio'
    data_save_file = './../data/dataset/dataset.txt'
    dp = DataPreparation(audio_path=audio_path, dataset_save_file=data_save_file)
    dp.prepare_data()


if __name__ == '__main__':
    main()
