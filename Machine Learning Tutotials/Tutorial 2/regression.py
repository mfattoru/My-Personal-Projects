import pandas as pd
import quandl
import math
import numpy as np    #computing library
from sklearn import preprocessing, cross_validation, svm
from sklearn.linear_model import LinearRegression

#preprocessing - we'll be using the scaling

df = quandl.get('WIKI/GOOGL')

# Get just the columns that we need
df = df[['Adj. Open','Adj. High','Adj. Low','Adj. Close','Adj. Volume']]
#Extract connections between the data we have available

df['HL_PCT'] = (df['Adj. High'] - df['Adj. Close']) / df['Adj. Close'] * 100.0
df['PCT_change'] = (df['Adj. Close'] - df['Adj. Open']) / df['Adj. Open'] * 100.0

df=df[['Adj. Close','HL_PCT','PCT_change','Adj. Volume']]

forecast_col = 'Adj. Close'

#fill the NaN with a number that we define,It will never be a good idea to sacrifice data in our dataset.
# a column might be missing, but another column might be there available in the same row and we don't want to
# discard that value
# the new value will be treated as an outlier in the dataset

df.fillna(-99999, inplace=True)

#forecast out (this is  regression algorithm) - usually we use regression algorithm to forecast out


#ceiling will get anything and round it to the nearest whole number
#we are trying to predict 10 percent of the dataframe (the 0.1)
forecast_out = int(math.ceil(0.01*len(df)))

#shift up label columns up
df['label'] = df[forecast_col].shift(-forecast_out)
df.dropna(inplace=True)

#print(df.head())
#features usually marked with a capital x, and y are the labels
#df.drop return a new dataframe with a dropped column,in this case label
X = np.array(df.drop(['label'],1))
y = np.array(df['label'])

X = preprocessing.scale(X)

X = X[:-forecast_out+1]

df.dropna(inplace=True)
y=np.array(df['label'])

print(len(X),len(y))











































