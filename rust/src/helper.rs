#[derive(Debug, Clone)]
#[repr(C)]
pub struct Vector2 {
    x: f32,
    y: f32,
}

const NUM_POINTS: usize = 30;

#[repr(C)]
pub struct PassData {
    points_array: [Vector2; NUM_POINTS],
}

#[no_mangle]
pub extern "C" fn create_polygon(d: *mut PassData) {
    unsafe {
        let centroid = calculate_centroid(&(*d).points_array);
        
        let mut sorted_points: [Vector2; NUM_POINTS] = (*d).points_array.clone();

        sorted_points.sort_by(|a, b| {
            let angle_a = (a.y - centroid.y).atan2(a.x - centroid.x);
            let angle_b = (b.y - centroid.y).atan2(b.x - centroid.x);
            angle_a.partial_cmp(&angle_b).unwrap()
        });

        (*d).points_array = sorted_points;
    }
}

fn calculate_centroid(points: &[Vector2]) -> Vector2 {
    let mut centroid = Vector2 { x: 0.0, y: 0.0 };
    for point in points {
        centroid.x += point.x;
        centroid.y += point.y;
    }
    centroid.x /= points.len() as f32;
    centroid.y /= points.len() as f32;
    centroid
}
