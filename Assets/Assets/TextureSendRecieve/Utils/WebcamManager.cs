using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

namespace TextureSendReceive {

	public class WebcamManager : MonoBehaviour {
    	[HideInInspector]
		public int webcamIndex = 0;
		public int width = 640;
		public int height = 480;
		public int fps = 30;

		[HideInInspector]
		public WebCamTexture texture;
		[HideInInspector]

		// Use this for initialization
		void Start () {
			// List connected cameras in console
         	for (int i = 0; i < WebCamTexture.devices.Length; i++) {
				print ("Webcam " + i + " available: " + WebCamTexture.devices[i].name);
         	}

			SetSelectedWebcam();
		}

		void SetSelectedWebcam() {
			// Stop previous webcam connection
			if(texture != null) texture.Stop();

			// assign and start selected webcam
        	texture = new WebCamTexture(WebCamTexture.devices[webcamIndex].name, width, height, fps);
        	texture.Play();
		}


        private void OnApplicationQuit() {
            if (texture != null && texture.isPlaying) {
                texture.Stop();
            }
        }		
	}
}