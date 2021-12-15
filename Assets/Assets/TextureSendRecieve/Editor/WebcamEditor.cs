using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace TextureSendReceive
{
	[CustomEditor(typeof(WebcamManager))]
	public class WebcamEditor : Editor
	{
		string[] webcams = new string[0];
		int webcam = 0;

		public override void OnInspectorGUI()
		{
			DrawDefaultInspector();

			// Update list of available webcams
			webcams = new string[WebCamTexture.devices.Length];
			for (int i = 0; i < webcams.Length; i++)
			{
				webcams[i] = WebCamTexture.devices[i].name;
			}

			// add GUI popup
			webcam = EditorGUILayout.Popup("Webcam", webcam, webcams);

			// Update property value in target class instance
			WebcamManager webcamManager = target as WebcamManager;
			webcamManager.webcamIndex = webcam;

			// Save the changes back to the object
			EditorUtility.SetDirty(target);
		}
	}
}
