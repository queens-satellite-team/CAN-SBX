# This code cleans up the message file created by the OBC and obtains the average current values for each sub-system
# Written by Kate Szabo
# Last updated August 12, 2021

import pandas as pd
import os

cwd = os.getcwd()
df = pd.read_csv(os.path.join(cwd, 'sample_data.txt'))

messages = df['Message']
message_arr = [['message']] * len(messages)
for entry, message in enumerate(messages):
    message_arr[entry] = message.split(' ')

message_df = pd.DataFrame.from_records(message_arr)
message_df[3] = message_df[3].str.replace(r'>', '')  # Remove > character from current vals
message_df = message_df[message_df[0] != '~']
message_df = message_df.drop([4])

message_df.columns = ['P1', 'P2', 'OBC', 'Comms', '1', '2', '3', '4', '5', '6']
message_df = message_df.drop(['1', '2', '3', '4', '5', '6'], axis=1)
message_df = message_df.drop([0, 1, 2], axis=0)


# message_df = message_df[message_df["Comms"].str.contains("<")==False]
# message_df = message_df[message_df.Comms.apply(lambda x: x.isnumeric())]
message_df['P1'] = pd.to_numeric(message_df['P1'], errors='coerce')
message_df['P2'] = pd.to_numeric(message_df['P2'], errors='coerce')
message_df['OBC'] = pd.to_numeric(message_df['OBC'], errors='coerce')
message_df['Comms'] = pd.to_numeric(message_df['Comms'], errors='coerce')

message_df = message_df.dropna()

df_mean = message_df[["P1", "P2", "OBC", "Comms"]].mean()
print(df_mean)

message_df.to_csv('current_values.csv', index=False)


