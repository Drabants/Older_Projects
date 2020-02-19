class CreateDirections < ActiveRecord::Migration
  def change
    create_table :directions do |t|
      t.text :step
      t.belongs_to :post, index: true, foreign_key: true

      t.timestamps null: false
    end
  end
end
