import scipy.signal as scisig
import numpy as np


class AudioUtils:
    def __init__(self):
        pass

    @staticmethod
    def _sgn(x):
        y = np.zeros_like(x)
        y[np.where(x >= 0)] = 1.0
        y[np.where(x < 0)] = -1.0
        return y

    @staticmethod
    def ste(data, wintype, winlen):
        """
        Compute short-time energy
        :param data:
        :param wintype:
        :param winlen:
        :return:
        """
        win = scisig.get_window(wintype, winlen)
        return scisig.convolve(data ** 2, win ** 2, mode="same")

    @staticmethod
    def stzcr(data, wintype, winlen):
        """
        Compute short-time zero crossing rate.
        :param data:
        :param wintype:
        :param winlen:
        :return:
        """
        win = scisig.get_window(wintype, winlen)
        win = 0.5 * win / len(win)
        x1 = np.roll(data, 1)
        x1[0] = 0.0
        abs_diff = np.abs(AudioUtils._sgn(data) - AudioUtils._sgn(x1))
        return scisig.convolve(abs_diff, win, mode="same")
