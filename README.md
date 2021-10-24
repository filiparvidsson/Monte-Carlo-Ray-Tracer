# Monte Carlo Ray Tracer

![scene](https://i.imgur.com/q9fl0Oe.png)

*An image created by this renderer*

---

Welcome to the README for this **Monte Carlo Ray Tracer**. A Monte Carlo Ray Tracer aims to create photo realistic images by sampling each pixel in the image many times.
In the image above 256 rays per pixel were used. The more rays, the better approximation you get.

The following is a brief description of some of the project components.

## Objects 📄
Objects are the primitiv shapes used to create the scene. So far, *triangel*, *sphere* and *box* has been implemented.

## Materials 🎨
Every object holds a pointer to a material that determines how rays interact with the object when hitting it and how the ray's radiance (color) is affected.
The materials that have been implemented are *DiffuseLambertian*, *Mirror* and *Glass*.

## Camera 📷
The camera holds the important functions *render* and *createImage* that initiates the whole rendering process. The image is created by sending rays from an observer,
through the camera plane and into the scene. The camera plane becomes the output image.

## Scene 🌏
The scene holds all the objects in 3D space. It also contains the vital *traceRay*-function that lets the ray bounce around between objects in the scene.

---

## The devs ☕
This application was developed as project work for the course TNCG15, Advanced Global Illumination and Rendering, at Linköping University by the following M.Sc. students in Media Technology:
- Måns Aronsson ([@mansaronsson](https://github.com/mansaronsson))
- Filip Arvidssson ([@paffnkpg](https://github.com/paffnkpg))
