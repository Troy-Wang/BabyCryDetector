from sklearn.pipeline import Pipeline
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.metrics import f1_score
from sklearn.metrics import accuracy_score
from sklearn.metrics import recall_score
from sklearn.metrics import precision_score
from sklearn.metrics import classification_report
from sklearn.metrics import make_scorer
import numpy as np


class ModelTraining:
    def __init__(self, X, y):
        self.X = X
        self.y = y
        pass

    def train_model(self):
        # split data
        X_train, X_test, y_train, y_test = train_test_split(self.X, self.y, stratify=self.y, test_size=0.2,
                                                            random_state=0)

        pipeline = Pipeline([('scaler', StandardScaler()), ('svm_clf', SVC(degree=3))])

        param_grid = [{'svm_clf__kernel': ['linear', 'poly', 'rbf'],
                       'svm_clf__C': np.logspace(-2, 2, 5),
                       'svm_clf__gamma': np.logspace(-3, 3, 7, base=2),
                       'svm_clf__coef0': np.logspace(0, -3, 4, base=2)}]

        def myf1score(actual, prediction):
            return f1_score(actual, prediction, average='macro')

        my_f1_scorer = make_scorer(myf1score, greater_is_better=True)

        estimator = GridSearchCV(pipeline, param_grid, cv=5, scoring=my_f1_scorer)

        model = estimator.fit(X_train, y_train)

        y_pred = model.predict(X_test)

        perf = {'accuracy': accuracy_score(y_test, y_pred),
                'recall': recall_score(y_test, y_pred, average='macro'),
                'precision': precision_score(y_test, y_pred, average='macro'),
                'f1': f1_score(y_test, y_pred, average='macro'),
                }

        return perf, model.best_estimator_
