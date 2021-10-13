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
You should already have LabVIEW installed before following these steps if you're using
LabVIEW.  For C++, you should have VSCode installed according to [WPILib Documentation](https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/index.html).

For LabVIEW ArgoBot v2, you will need [CTRE Phoenix](http://www.ctr-electronics.com/hro.html#product_tabs_technical_resources) installed as well.

* TOC
{:toc}

## C++

<details markdown="block" open>

### Clone Training Files From GitHub
1. Open VSCode
2. Click the "Source Control" icon in the sidebar (or press <kbd>Ctrl</kbd> + <kbd>Shift</kbd> +<kbd>G</kbd>) and choose "Clone Repository"
   ![VSCode Source Control Menu]({{ baseImagePath }}/VSCode_Clone_0.png)
3. In the prompt, enter `https://github.com/FRC1756-Argos/ArgoBot-Drive-Training.git` and press <kbd>Enter</kbd>.
   ![VSCode Clone]({{ baseImagePath }}/VSCode_Clone_1.png)
4. Save in a memorable location.  For example, create a Git folder inside your Documents folder and select it.
5. In the same Source Control Menu, choose "Open Folder".
6. In the dialog box, navigate to the src/C++ folder inside the Argobot-Drive-Training folder you cloned in step 4.
   ![VSCode Open]({{ baseImagePath }}/VSCode_Clone_2.png)
7. You should now have a fresh project open that looks like this:
   ![VSCode Fresh Project]({{ baseImagePath }}/VSCode_Fresh_Project.png)

</details>

## LabVIEW

<details markdown="block">

### Install LINX \(ArgoBot v1 Only\)

LINX is a platform to run LabVIEW code on various embedded devices.
ArgoBots use LINX, so we will install this library to begin.

1. Go to the [NI LINX page](http://sine.ni.com/nips/cds/view/p/lang/en/nid/212478)
2. Click the "LINX Download" link in the resources tab
3. Click the "Download Toolkit" button at the top of the page.  This will launch the LabVIEW VI Package Manager
4. In the LabVIEW Package Manager window, click the Install button.  This may take a while and may need to install additional libraries.
   ![VIPM Install Window]({{ baseImagePath }}/LINX_VIPM.png)
5. If the installation completes successfully, you should see a confirmation that looks like the image below
   ![VIPM Success Window]({{ baseImagePath }}/LINX_VIPM_Success.png)

### Clone Training Files From GitHub

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

### Verify Environment

Now that everything's ready, let's make sure all the pieces are working.

#### ArgoBot v1

1. In the GitHub desktop client, select "Repository">"Show in Explorer"
   ![GitHub Explore]({{ baseImagePath }}/Verify_0.png)
2. In the `src/ArgobotV1` folder, open `ArgoBot_Main.vi`
   ![Explorer Navigate]({{ baseImagePath }}/Verify_1.png)
3. Make sure the run arrow is solid white as shown below
   ![Open Code]({{ baseImagePath }}/Verify_2.png)

#### ArgoBot v2

1. In the GitHub desktop client, select "Repository">"Show in Explorer"
   ![GitHub Explore]({{ baseImagePath }}/Verify_0.png)
2. In the `src/ArgobotV2` folder, open `ArgoBotV2.lvproj`
   ![Explorer Navigate]({{ baseImagePath }}/Verify_1_v2.png)
3. Open `Robot Main.vi` in the project explorer window
   ![Project Explorer]({{ baseImagePath }}/Verify_2_v2.png)
4. Make sure the run arrow is solid white as shown below
   ![Open Code]({{ baseImagePath }}/Verify_3_v2.png)

</details>

Congratulations!  You're ready to start the training exercises!  Click the link below to begin the first tutorial.

| ------------------- |:-------------:| --------------:|
| [<-Previous][PREV]  | [Index][HOME] | [Next->][NEXT] |
