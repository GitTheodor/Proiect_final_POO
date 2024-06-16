#include "pch.h"
#include <msclr/marshal.h>
#include <list>
using namespace System;
using namespace System::Collections::Generic;




public ref class Comment {
private:
    String^ content;
    String^ userName;

public:
    // Constructor
    Comment(String^ content, String^ userName) {
        this->content = content;
        this->userName = userName;
    }

    property String^ Content {
        String^ get() {
            return content;
        }
    }

    property String^ UserName {
        String^ get() {
            return userName;
        }
    }
};
public ref class Video {
private:
    String^ title;
    List<Comment^>^ comments;

public:
    // Constructor
    Video(String^ title) {
        this->title = title;
        comments = gcnew List<Comment^>();
    }

    // Destructor
    ~Video() {
        Console::WriteLine("Video '{0}' deleted.", title);
    }
    void AddComment(String^ content, String^ userName) {
        comments->Add(gcnew Comment(content, userName));
        Console::WriteLine("{0} commented on '{1}': {2}", userName, title, content);
    }
    
    property String^ Title {
        String^ get() {
            return title;
        }
    }
};

public ref class User {
private:
    String^ name;
    bool subscribed;
    int likes;
    int dislikes;
    List<Video^>^ uploadedVideos;

public:
    // Constructor
    User(String^ name) {
        this->name = name;
        subscribed = false;
        likes = 0;
        dislikes = 0;
        uploadedVideos = gcnew List<Video^>();
    }

    // Destructor
    ~User() {
        Console::WriteLine("User '{0}' deleted.", name);
    }
    void AddUploadedVideo(Video^ video,String^ title) {
        uploadedVideos->Add(video);
        Console::WriteLine("{0} posted video: {1}", name, title);
    }
    void AddCommentToVideo(String^ videoTitle, String^ comment) {
        for (int i = 0; i < uploadedVideos->Count; i++) {
            if (uploadedVideos[i]->Title == videoTitle) {
                uploadedVideos[i]->AddComment(name, comment);  // Call video's AddComment
                return;
            }
        }
        Console::WriteLine("Video '{0}' not found for commenting!", videoTitle);
    }
    // Function to subscribe
    void Subscribe() {
        subscribed = true;
        Console::WriteLine("{0} subscribed!", name);
    }

    // Function to like a video
    void LikeVideo() {
        likes++;
        Console::WriteLine("{0} liked a video!", name);
    }

    // Function to dislike a video
    void DislikeVideo() {
        dislikes++;
        Console::WriteLine("{0} disliked a video!", name);
    }

    // Function to post video
    //void PostVideo(String^ title) {
       // uploadedVideos->Add(gcnew Video(title));
       // Console::WriteLine("{0} posted video: {1}", name, title);
   // }

    // Function to delete video by title
    void DeleteVideo(String^ title) {
        for (int i = 0; i < uploadedVideos->Count; i++) {
            if (uploadedVideos[i]->Title == title) {
                uploadedVideos->RemoveAt(i);
                Console::WriteLine("{0} deleted video: {1}", name, title);
                return;
            }
        }
        Console::WriteLine("Video '{0}' not found for deletion!", title);
    }

    
    void PrintVideoDetails() {
        Console::WriteLine("  Name: {0}", name);
        Console::WriteLine("  Subscribed: {0}", subscribed ? "Yes" : "No");
        Console::WriteLine("  Likes: {0}", likes);
        Console::WriteLine("  Dislikes: {0}", dislikes);
        Console::WriteLine("  Uploaded Videos:");
        for each (Video ^ video in uploadedVideos) {
            Console::WriteLine("    - {0}", video->Title);
        }
    }
};

int main(array<String^>^ args) {
    // Create users and videos
    User^ user1 = gcnew User("Alice");
    User^ user2 = gcnew User("Bob");
    Video^ video1 = gcnew Video("C++/CLI Tutorial");
    Video^ video2 = gcnew Video("Funny Cat Compilation");

    // User actions
    user1->Subscribe();
    user2->LikeVideo();
    
    user1->AddUploadedVideo(video1, "C++/CLI Tutorial");
    user2->AddUploadedVideo(video2,"Funny Cat Compilation");
    user1->LikeVideo();
    user1->AddCommentToVideo(video1->Title, "Great tutorial!");
    user1->DeleteVideo(video2->Title); // This will fail

    // Print user information (including uploaded videos)
    Console::WriteLine("\nUser Information:");
    user1->PrintVideoDetails();
    user2->PrintVideoDetails();

    Console::ReadKey();
    return 0;
}
