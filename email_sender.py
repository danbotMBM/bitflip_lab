from __future__ import print_function
import os.path
import base64
import pickle
import os.path
import google.auth
import google.auth.transport.requests
from email.mime.text import MIMEText
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these SCOPES, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/gmail.send']

subscribers = ["danielmarkjones9@gmail.com", "djjones925@yahoo.com"]

def send_email(subject, body):
    """Shows basic usage of the Gmail API.
    Lists the user's Gmail labels.
    """
    creds = None
    # The file token.pickle stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    try:
        # Call the Gmail API
        service = build('gmail', 'v1', credentials=creds)
        
        message = MIMEText(str(body))
        message['to'] = 'danielmarkjones9@gmail.com'
        message['from'] = 'danbotlab@gmail.com'
        message['subject'] = str(subject)
        
        raw = base64.urlsafe_b64encode(message.as_bytes()).decode()
        body = {'raw': raw}

        sent_message = service.users().messages().send(userId="me", body=body).execute()
        print('Message Id: %s' % sent_message['id'])

    except HttpError as error:
        print(f'An error occurred: {error}')

if __name__ == '__main__':
    send_email()
