---
title: "Tutorial 0: Setup"
permalink: /tutorials/0/index.html
---
[PREV]: {{site.baseurl}}/index.html
[HOME]: {{site.baseurl}}/index.html
[NEXT]: {{site.baseurl}}/tutorials/1/index.html

{% capture baseImagePath %}{{ site.baseurl }}/assets/images/tutorials/0{% endcapture %}

# Tutorial 0: Setup

Welcome!  In this tutorial, you will set up your computer to run the other tutorials.
If you already have your computer set up, you can move on to [the first exercise][NEXT].
You should already have LabVIEW installed before following these steps.

* TOC
{:toc}

## Install LINX

LINX is a platform to run LabVIEW code on various embedded devices.
ArgoBots use LINX, so we will install this library to begin.

1. Go to the [NI LINX page](http://sine.ni.com/nips/cds/view/p/lang/en/nid/212478)
2. Click the "LINX Download" link in the resources tab
3. Click the "Download Toolkit" button at the top of the page.  This will launch the LabVIEW VI Package Manager
4. In the LabVIEW Package Manager window, click the Install button.  This may take a while and may need to install additional libraries.
   ![VIPM Install Window]({{ baseImagePath }}/LINX_VIPM.png)
5. If the installation completes successfully, you should see a confirmation that looks like the image below
   ![VIPM Success Window]({{ baseImagePath }}/LINX_VIPM_Success.png)

## Clone Training Files From GitHub

All the files for these exercises are hosted on GitHub, a Git repository host.
Git is a version control system that enables us to archive, share, and collaborate on software projects.
You may use any git client to clone this repository, but I've included the GitHub GUI instructions because it offers a user-friendly experience.

1. Download and install the GitHub desktop client from [GitHub's website](https://desktop.github.com/)
  - If you have a GitHub account, you can sign in during the installation process.  You can also create a free account
2. Click the "Clone a repository button" on the GitHub client start page
   ![GitHub Clone Repo]({{ baseImagePath }}/GitHub_Clone_0.png)
3. Choose the URL `https://github.com/FRC1756-Argos/ArgoBot-Drive-Training.git` and a location on your computer to download the files to
   ![GitHub Clone URL]({{ baseImagePath }}/GitHub_Clone_1.png)
4. Make sure you have the master branch checked out
   ![GitHub Checkout]({{ baseImagePath }}/GitHub_Clone_2.png)

## Verify Environment

Now that everything's ready, let's make sure all the pieces are working.

1. In the GitHub desktop client, select "Repository">"Show in Explorer"
   ![Open Code]({{ baseImagePath }}/Verify_0.png)
2. In the `src` folder, open `ArgoBot_Main.vi`
   ![Open Code]({{ baseImagePath }}/Verify_1.png)
3. Make sure the run arrow is solid white as shown below
   ![Open Code]({{ baseImagePath }}/Verify_2.png)

Congratulations!  You're ready to start the training exercises!  Click the link below to begin the first tutorial.

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
