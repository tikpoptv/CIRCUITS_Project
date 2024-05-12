import face_recognition
import pickle

ryu_img = face_recognition.load_image_file("/Users/phattharapongduangkham/Documents/KMUTT/Proj_Room_Sec/CIRCUITS_Project/face_id/Pics/Ryu_6.jpg")
ryu_faceen = face_recognition.face_encodings(ryu_img)[0]

tik_img = face_recognition.load_image_file("/Users/phattharapongduangkham/Documents/KMUTT/Proj_Room_Sec/CIRCUITS_Project/face_id/Pics/Tik_8.jpg")
tik_faceen = face_recognition.face_encodings(tik_img)[0]

# Save the face recognition model
known_faces = {"Ryu": ryu_faceen, "Tik": tik_faceen}
with open("known_faces.pkl", "wb") as f:
    pickle.dump(known_faces, f)