import pickle
from flask import Flask, Response
import face_recognition
import cv2
import numpy as np

app = Flask(__name__)

# Load the saved model
with open("/Users/jedsadapornpannok/Library/CloudStorage/OneDrive-KingMongkut’sUniversityofTechnologyThonburi(KMUTT)/Study/year-1-Trem-2/GEN121/Final_Project/CIRCUITS_Project/face_id/model/known_faces.pkl", "rb") as f:
    known_faces = pickle.load(f)

video_capture = cv2.VideoCapture(1)

def detect_face():
    ret, frame = video_capture.read()
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
    output = cv2.cvtColor(small_frame, cv2.COLOR_BGR2RGB)

    # Find all the faces and face encodings in the current frame of video
    face_locations = face_recognition.face_locations(output)
    face_encodings = face_recognition.face_encodings(output, face_locations)

    # Loop over each face found in the frame to see if it's someone we know.
    for face_encoding in face_encodings:
        # See if the face is a match for the known face(s)
        for name, known_face_encoding in known_faces.items():
            match = face_recognition.compare_faces([known_face_encoding], face_encoding)
            if match[0]:
                return name

    return "Unknown Person"

@app.route('/')
def index():
    name = detect_face()
    return """<meta http-equiv="refresh" content="1"> <h1> {} </h1>""".format(name)

if __name__ == '__main__':
    app.run(debug=True)
