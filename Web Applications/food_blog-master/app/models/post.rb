
class Post < ActiveRecord::Base
    has_many :ingredients
    has_many :comments, dependent: :destroy
    has_many :directions
    
    accepts_nested_attributes_for :ingredients, reject_if: :all_blank, allow_destroy: true
    accepts_nested_attributes_for :directions, reject_if: :all_blank, allow_destroy: true
    
    validates :title, presence: true, length: {minimum: 5}
    validates :body, :photo, presence: true
    has_attached_file   :photo,
                :default_url => "/images/:style/missing.png",
                :url  => ":s3_domain_url",
                :path => "public/photos/:id/:style_:basename.:extension",
                :storage => :fog,
                :fog_credentials => {
                    provider: 'AWS',
                    aws_access_key_id: ENV["AWS_ACCES_KEY_ID"],
                    aws_secret_access_key: ENV["AWS_SECRET_ACCESS_KEY"]
                },
                fog_directory: ENV["FOG_DIRECTORY"], 
                :styles => { :medium => "640x360>", :thumb => "450x450" }
                
    validates_attachment_content_type :photo, content_type: /\Aimage\/.*\z/
end